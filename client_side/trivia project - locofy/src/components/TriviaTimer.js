import React, { useEffect, useState, useRef } from 'react';
import { FaClock } from 'react-icons/fa';
import styles from './TriviaTimer.module.css';

const Stopwatch = ({ initialTime, onTimeUp }) => {
  const [time, setTime] = useState(initialTime);
  const timerRef = useRef(null);

  useEffect(() => {
    timerRef.current = setInterval(() => {
      setTime((prevTime) => {
        if (prevTime <= 10) {
          clearInterval(timerRef.current);
          onTimeUp();
          return 0;
        }
        return prevTime - 10;
      });
    }, 10);

    return () => {
      clearInterval(timerRef.current);
    };
  }, [onTimeUp]);

  const formatTime = (time) => {
    const seconds = Math.floor(time / 1000);
    const milliseconds = time % 1000;
    return `${seconds}.${milliseconds.toString().padStart(3, '0')}`;
  };

  return (
    <div className={styles.stopwatch}>
      <FaClock className={styles.clockIcon} />
      <span className={styles.time}>{formatTime(time)}</span>
    </div>
  );
};

export default Stopwatch;
