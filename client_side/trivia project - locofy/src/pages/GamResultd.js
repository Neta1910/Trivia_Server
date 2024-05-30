import { useEffect, useState } from 'react';
import PlayerRes from '../components/PlayerRes'
import styles from "./GamResultd.module.css";
import { socket } from '../socket';
import Constants from '../Constants';

const GamResultd = () => {
  const [gameResults, setGameResults] = useState([])
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    socket.on("getRoomResResponse", (response) => {
      if (response.status === Constants.WORK_STATUS) {
        setGameResults(response[Constants.FIELDS.RESULTS])
        setLoading(false);
      }
    })

    socket.emit("getRoomRes");
    
    const intervalId = setInterval(() => {
      if (loading) {
        socket.emit("getRoomRes")
      }
    }, 3000); // 3 seconds interval

    return (
      () => {
        clearInterval(intervalId);
        socket.off("getRoomResResponse")
      }
    )
  }, [loading])

  return (
    <div className={styles.gamResultd}>
      <div className={styles.gameResult}>
        <div className={styles.itWasA}>
          It was a fun game, this is the results
        </div>
      </div>
      <section className={styles.playerResults}>
        
        {gameResults.map((element, index) => <PlayerRes 
          Playername={element[Constants.FIELDS.USER_NAME]}
          correctAns={element[Constants.FIELDS.CORRECT_ANSWER_COUNT]}
          avgTime={element[Constants.FIELDS.AVERAGE_ANSWER_TIME]}
          place={index}
        /> )}
      </section>
    </div>
  );
};

export default GamResultd;
