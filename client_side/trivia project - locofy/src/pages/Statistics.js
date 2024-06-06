import HighhScoreres from "../components/HighhScoreres";
import StatProperties from "../components/StatProperties";
import styles from "./Statistics.module.css";
import PieChart from "../components/PieChart";
import { useEffect, useState } from "react";
import { socket } from "../socket";
import Constants from "../Constants";

const Statistics = () => {
  const [totalAns, setTotalAns] = useState(0);
  const [avgAnsTime, setAvgAnsTime] = useState(0);
  const [gamesPlayed, setGamesPlayed] = useState(0);
  const [highScore, setHighScore] = useState(0);
  const [rightAns, setRightAns] = useState(0);

  const [isLoading, setIsLoading] = useState(true);
  const [errorInPersonal, setErrorInPersonal] = useState(false);

  useEffect (() => {  
    socket.on("getPersonalStats", (response) => {
      if (response.status === Constants.WORK_STATUS) {
        setAvgAnsTime(response[Constants.FIELDS.AVERAGE_ANSWER_TIME])
        setGamesPlayed(response[Constants.FIELDS.GAMES_PLAYED])
        setHighScore(response[Constants.FIELDS.HIGH_SCORE])
        setRightAns(response[Constants.FIELDS.CORRECT_ANSWER_COUNT])
        setTotalAns(response[Constants.FIELDS.TOTAL_ANS])
        setIsLoading(false);
      }
      else {
        setErrorInPersonal(true);
        setIsLoading(false);
      }
    })
    
    socket.emit("getPersonalStats");

    return (
      () =>
      socket.off("getPersonalStats")
    )
  }, [])
  return (
    <div className={styles.statistics}>
      <section className={styles.highhScoreresParent}>
        <HighhScoreres />
         {isLoading ? <p>Loading data</p> :
         errorInPersonal ? <p>The user havent played any games </p> :
         <PieChart 
            correctAns={rightAns}
            sumAns={totalAns}
         />
         }
      </section>
      {isLoading ? <p>Loading data</p> :
         errorInPersonal ? <p>The user havent played any games </p> :
         <StatProperties
            numOfGames={gamesPlayed}
            highScore={highScore}
            avgTime={avgAnsTime}
         />
         }
    </div>
  );
};

export default Statistics;
