import { useEffect } from 'react';
import { useTimer } from 'react-timer-hook';

function Timer({ timeOut, onExpire, reset }) {
  const expiryTimestamp = new Date(timeOut * 1000);
  const {
    totalSeconds,
    start,
    pause,
    resume,
    restart,
  } = useTimer({ expiryTimestamp, onExpire: () => onExpire(3)});

  useEffect(() => {
    if (reset) {
      restart(expiryTimestamp);
    }
  }, [reset, timeOut, restart, expiryTimestamp]);

  return (
    <div style={{ textAlign: 'center' }}>
      <p>Time Left</p>
      <div style={{ fontSize: '100px' }}>
        <span>{totalSeconds}</span>
      </div>
    </div>
  );
}

export default Timer;
