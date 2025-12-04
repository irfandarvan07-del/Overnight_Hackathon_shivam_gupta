#include "detector.h"
#include <cmath>
#include <sstream>
#include <iostream>

static double mean(const std::vector<double>& v) {
    if (v.empty()) return 0.0;
    double s=0;
    for (double x: v) s+=x;
    return s / v.size();
}
static double stddev(const std::vector<double>& v, double m) {
    if (v.size() < 2) return 0.0;
    double s=0;
    for (double x: v) s += (x - m)*(x - m);
    return std::sqrt(s / (v.size()));
}

std::vector<DetectionResult> run_detection(const std::vector<Txn> &txns) {
    std::vector<DetectionResult> results;
    std::map<std::string, std::vector<double>> amounts_by;
    for (auto &t: txns) amounts_by[t.from_vpa].push_back(t.amount);

    std::map<std::string, std::pair<double,double>> stats;
    for (auto &kv: amounts_by) {
        double m = mean(kv.second);
        double sd = stddev(kv.second, m);
        stats[kv.first] = {m, sd};
    }

    std::map<std::string,int> small_count;
    for (auto &t: txns) if (t.amount < 20.0) small_count[t.from_vpa] += 1;

    for (auto &t: txns) {
        DetectionResult dr;
        dr.txn = t;
        dr.rules = apply_rules(t);
        dr.stat_anomaly = false;
        dr.severity = 0;

        if (small_count[t.from_vpa] >= 3 && t.amount < 20.0) {
            dr.rules.micro_cluster = true;
            dr.rules.reasons.push_back("micro_cluster");
        }

        auto it = stats.find(t.from_vpa);
        if (it != stats.end()) {
            double m = it->second.first;
            double sd = it->second.second;
            double z = 0.0;
            if (sd > 0.00001) z = (t.amount - m) / sd;
            if (std::fabs(z) > 3.0 || (m < 100.0 && t.amount > 1000.0)) {
                dr.stat_anomaly = true;
            }
        }

        bool any_rule = !dr.rules.reasons.empty();
        if (any_rule) dr.severity += 2;
        if (dr.stat_anomaly) dr.severity += 1;

        std::ostringstream oss;
        if (!dr.rules.reasons.empty()) {
            for (size_t i=0;i<dr.rules.reasons.size();++i) {
                if (i) oss << ";";
                oss << dr.rules.reasons[i];
            }
        }
        if (dr.stat_anomaly) {
            if (!dr.rules.reasons.empty()) oss << ";";
            oss << "stat_anomaly";
        }
        dr.why = oss.str();
        results.push_back(dr);
    }

    return results;
}

