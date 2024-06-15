import { useEffect, useState } from 'react';
import PlayerRes from '../components/PlayerRes'
import styles from "./GamResultd.module.css";
import { socket } from '../socket';
import Constants from '../Constants';
import { useNavigate } from 'react-router-dom';

const GamResultd = () => {
  const [gameResults, setGameResults] = useState([])
  const [loading, setLoading] = useState(true);
  const navigate = useNavigate();
  useEffect(() => {
    socket.on("getRoomResResponse", (response) => {
      console.log('response:', response)
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
          {loading ? "there are still players who didnt finsh the game" : "It was a fun game, this is the results" } 
        </div>
      </div>
      <section className={styles.playerResults}>
        
        {gameResults.map((element, index) => <PlayerRes 
          Playername={element[Constants.FIELDS.USER_NAME]}
          correctAns={element[Constants.FIELDS.CORRECT_ANSWER_COUNT]}
          avgTime={element[Constants.FIELDS.AVERAGE_ANSWER_TIME]}
          place={index}
          key={index}
        /> )}
         
      </section>
      <section className={styles.backToMenuDiv} >
          <button className={styles.backToMenuButton} onClick={() => navigate("/Menu")}> Back to menu </button>
      </section>
    </div>
  );
};

export default GamResultd;
