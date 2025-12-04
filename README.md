# UPI Transaction Fraud Detector (The 8th Mile Hackathon Build)
"Because losing money to a QR code scam shouldn't be a thing."
Hey! Thanks for checking out our submission for the 8th Mile Hackathon. We decided to tackle something that annoys (and scares) pretty much everyone: UPI Fraud. You know those "accidentally sent you money" scams or the shady QR codes? We built a prototype to catch those in real-time before the money actually leaves your account.

##  💡 The Big Idea
We didn't want to just build a simple rule-checker. Scammers are smart, so our code needs to be smarter. We built a Hybrid Engine that thinks in two ways:

The "By the Book" Cop (Rule Engine): Checks for obvious red flags we know about, like micro-transactions meant to verify an account or fake refund patterns. Built in C++ for blazing-fast performance.
The "Gut Feeling" Cop (Machine Learning): We trained an IsolationForest model to look at the data and spot weird anomalies that don't fit the usual patterns, even if they pass the specific rules.


###    What's Inside?

A Live Dashboard: We whipped up a UI using HTML/CSS/JavaScript with Python handling the backend API. It visualizes the transaction flow so you can actually see the fraud getting flagged in real-time.
Synthetic Data: Obviously, we don't have access to private bank records (we'd be in jail). So, we wrote a script to generate realistic-looking transaction data to train our model.
Hybrid Logic: The cool part is how the C++ Rule Engine and the Python ML model talk to each other via REST API to give a final "Safe" or "Suspicious" verdict.


(IMP) The Tech Stack
We kept it lean and mean for the hackathon:
Backend:

C++ does the heavy lifting for rule-based fraud detection (fast, efficient, production-ready)
Python powers the ML anomaly detection engine
Flask/FastAPI bridges the C++ and Python services via REST API

Frontend:

HTML/CSS for the UI structure and styling
JavaScript for interactivity and real-time updates
Chart.js or similar for data visualization

ML & Data:

Scikit-Learn powers the anomaly detection
Pandas manages the messy data
NumPy for numerical operations


🗺️ A Tour of the Code
If you're diving into the files, here's where everything lives:
├── backend/
│   ├── cpp/                   👉 C++ Rule Engine (compiles to binary)
│   │   ├── src/              
│   │   ├── include/          
│   │   └── CMakeLists.txt    
│   └── python/                👉 ML Model & API Gateway
│       ├── app.py            
│       ├── ml_engine.py      
│       └── requirements.txt  
│
├── frontend/
│   ├── index.html             👉 Main dashboard UI
│   ├── styles/
│   │   └── main.css           👉 All the styling magic
│   └── scripts/
│       └── dashboard.js       👉 Real-time updates & API calls
│
├── scripts/                   👉 Tools we used to create fake data
│   └── generate_data.py      
│
├── notebooks/                 👉 Our digital scratchpad
│   └── model_experiments.ipynb 👉 Where we tested ML models
│
├── models/                    👉 (Git ignored) Trained models live here
└── data/                      👉 (Git ignored) CSVs and training data



this is not the final over viwe plz wait


t
