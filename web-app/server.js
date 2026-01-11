const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const path = require('path');

const app = express();
const PORT = 3000;

// Middleware
app.use(cors());
app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, 'public')));

// In-memory storage for the latest sensor data
let latestData = {
    temperature: 0,
    humidity: 0,
    heater: "false",
    timestamp: new Date().toISOString()
};

// History array to store past readings (for graphing)
const history = [];
const MAX_HISTORY = 50; // Keep last 50 readings

// API Endpoint to receive data from ESP32
app.post('/api/data', (req, res) => {
    const { temperature, humidity, heater } = req.body;

    if (temperature === undefined || humidity === undefined) {
        return res.status(400).json({ error: 'Invalid data format' });
    }

    latestData = {
        temperature,
        humidity,
        heater,
        timestamp: new Date().toISOString()
    };

    // Add to history
    history.push(latestData);
    if (history.length > MAX_HISTORY) {
        history.shift(); // Remove oldest
    }

    console.log(`Received Data - Temp: ${temperature}°C, Hum: ${humidity}%, Heater: ${heater}`);
    res.status(200).json({ message: 'Data received successfully' });
});

// API Endpoint for Frontend to get latest data
app.get('/api/data', (req, res) => {
    res.json(latestData);
});

// API Endpoint for Frontend to get history data
app.get('/api/history', (req, res) => {
    res.json(history);
});

// Start Server
app.listen(PORT, '0.0.0.0', () => {
    console.log(`Server running on http://0.0.0.0:${PORT}`);
    console.log(`Accessible locally at http://localhost:${PORT}`);
});
