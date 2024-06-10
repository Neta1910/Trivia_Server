import { useEffect } from 'react';
import { useTimer } from 'react-timer-hook';

function Timer({ timeOut, onExpire, reset }) {
  const {
    totalSeconds,
    seconds,
    minutes,
    hours,
    days,
    isRunning,
    start,
    pause,
    resume,
    restart,
  } = useTimer({ expiryTimestamp, onExpire: () => onExpire });

  useEffect( () => {
    const expiryTimestamp = new Date(timeOut * 1000);
    if (reset) restart (expiryTimestamp)
  }, [[reset, timeOut, restart]])

  return (
    <div style={{textAlign: 'center'}}>
      <p>time left</p>
      <div style={{fontSize: '100px'}}>
        <span>{totalSeconds}</span>
      </div>
    </div>
  );   
}

export default Timer