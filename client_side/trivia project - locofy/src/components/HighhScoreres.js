import styles from "./HighhScoreres.module.css";
import PlayerInHigh from "./PlayerInHigh";
import {socket} from '../socket'
import { useState } from "react";
import { useEffect } from "react";
import Constents from '../Constants'

const HighhScoreres = () => {
  
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState(false);
  const [highScores, setHighScores] = useState([]);

  useEffect(() => {
    socket.on("getHighScoreResponse", (response) => {
      if (response.status === Constents.WORK_STATUS) {
          setHighScores(response.statistics);
          setIsLoading(false);
        }
      else {
        setError(true);
        setIsLoading(false);
      }
    })
  })

  return (
    <div className={styles.highhScoreres}>
      {isLoading ? <p> still loading </p> : 
      error ? <p>Error, try agein</p> :
      highScores.length === 0 ? <p>There is no elements in the stats, try agein</p> :
      highScores.map ((stat, index) => {
        <PlayerInHigh 
          place={index}
          userName={stat[Constents.FIELDS.USER_NAME]}
          score={stat[Constents.FIELDS.HIGH_SCORE]}
        />
      })}
    </div>
  );
};

export default HighhScoreres;
