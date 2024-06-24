import React, { useState, useEffect } from 'react';

function NetworkMonitor() {
  const [logs, setLogs] = useState([]);

  useEffect(() => {
    const interval = setInterval(() => {
      fetch('/api/logs')
        .then(response => response.json())
        .then(data => setLogs(data))
        .catch(error => console.error('Error fetching logs:', error));
    }, 5000); // Fetch logs every 5 seconds

    return () => clearInterval(interval);
  }, []);

  return (
    <div className="p-4">
      <h2 className="text-xl font-bold mb-4">Network Monitor</h2>
      <div className="overflow-y-auto max-h-64">
        {logs.map((log, index) => (
          <p key={index} className="mb-1 p-2 border-b">{log}</p>
        ))}
      </div>
    </div>
  );
}

export default NetworkMonitor;
