import React from 'react';
import './App.css';
import { BrowserRouter as Router, Routes, Route, Navigate } from "react-router-dom";
import Home from './Home'

function App() {
  return (
    <Router>
      <div className="App">
        <header className="Header">
          <Routes>
            <Route exact path='/'/>
              <Navigate to='/home'/>
            <Route/>
              <Route path="/home" exact component={Home}>
              <Home/>
            </Route>
          </Routes>
        </header>
      </div>
    </Router>
  );
}

export default App;