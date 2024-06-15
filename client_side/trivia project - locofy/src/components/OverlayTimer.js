import React, { useState, useEffect } from 'react';

const CountdownOverlay = ({ action }) => {
  const [countdown, setCountdown] = useState(5);

  useEffect(() => {
    const timer = countdown > 0 && setInterval(() => setCountdown(countdown - 1), 1000);
    return () => clearInterval(timer);
  }, [countdown]);

  useEffect(() => {
    if (countdown === 0) {
      action(); // Perform the desired action when countdown reaches 0
    }
  }, [countdown, action]);

  return (
    <div style={{
      position: 'fixed',
      top: 0,
      left: 0,
      width: '100%',
      height: '100%',
      display: 'flex',
      justifyContent: 'center',
      alignItems: 'center',
      backgroundColor: 'rgba(0, 0, 0, 0.5)',
      zIndex: 9999,
      color: 'white',
      fontSize: '5rem',
    }}>
      {countdown}
    </div>
  );
};

export default CountdownOverlay;