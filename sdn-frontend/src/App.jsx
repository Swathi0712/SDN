import React from 'react';
import './App.css'
import { BrowserRouter as Router, Route,Routes } from 'react-router-dom';
import SwitchList from './components/switchList';
import RoutingTable from './components/RoutingTable';
import NetworkMonitor from './components/NetworkMonitor';

function App() {
  return (
    <Router>
      <div className="container mx-auto p-4 text-black bg-slate-300">
        <header className="mb-4">
          <h1 className="text-2xl font-bold">SDN Controller Dashboard</h1>
          {/* <nav className="mt-2">
            <a href="/" className="mr-4">Switches</a>
            <a href="/routing-table" className="mr-4">Routing Table</a>
            <a href="/network-monitor">Network Monitor</a>
          </nav> */}
        </header>
        {/* <Routes>
          <Route exact path="/" component={SwitchList} />
          <Route path="/routing-table" component={RoutingTable} />
          <Route path="/network-monitor" component={NetworkMonitor} />
        </Routes> */}
        <SwitchList/>
        <RoutingTable/>
      </div>
    </Router>
  );
}

export default App;
