import React, { useState, useEffect } from 'react';

function RoutingTable() {
  const [routingTable, setRoutingTable] = useState([]);

  useEffect(() => {
    console.log('fetching the api')
    fetch('http://localhost:8000/routingTable')
      .then(response =>response.json())
      .then(data => setRoutingTable(data["routingTable"]))
      .catch(error => console.error('Error fetching routing table:', error));
  }, []);

  return (
    <div className="p-4 rounded-md">
      <h2 className="text-xl font-bold mb-4 rounded-md">Routing Table</h2>
      <table className="min-w-full bg-white border rounded-md">
        <thead>
          <tr>
            <th className="py-2 px-4 border">Destination</th>
            <th className="py-2 px-4 border">Next Hops</th>
            <th className="py-2 px-4 border">Cost</th>
          </tr>
        </thead>
        <tbody>
          {routingTable.map(entry => (
            <tr key={entry.destination}>
              <td className="py-2 px-4 border">{entry.destination}</td>
              <td className="py-2 px-4 border">{entry.nextHops.join(', ')}</td>
              <td className="py-2 px-4 border">{entry.cost}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}

export default RoutingTable;
