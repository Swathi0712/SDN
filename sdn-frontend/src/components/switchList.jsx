import React, { useState, useEffect } from 'react';

function SwitchList() {
  const [switches, setSwitches] = useState([]);

  useEffect(() => {
    fetch('http://localhost:8000/switches')
      .then((response )=> response.json())
      .then(data => {
        console.log(data);
        setSwitches([...data["switches"]])})
      .catch(error => console.error('Error fetching switches:', error));
      console.log(switches);
  }, []);

  return (
    <div className="p-4">
      <h2 className="text-xl font-bold mb-4">Switches</h2>
      <ul>
        {switches.map((sw,idx) => (
          <li key={idx} className="mb-2 p-2 border rounded shadow">
            {/* {sw.name} - IP: {sw.ip} */}
            {sw}
          </li>
        ))}
      </ul>
    </div>
  );
}

export default SwitchList;
