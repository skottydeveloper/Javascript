import React from 'react';
import './App.css';
import { BrowserRouter as Router, Routes, Route, Navigate } from "react-router-dom";
import Home from './Home'

function App() {
  return (
    <Router>
      <div className="App">
        <header className="App-header">
          <Routes>
            <Route path="/" element={<Navigate to="/home" />} />
            <Route path="/home" element={<Home />} />
          </Routes>
        </header>
      </div>
    </Router>
  );
}

export default App;