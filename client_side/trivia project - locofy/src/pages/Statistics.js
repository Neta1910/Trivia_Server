import HighhScoreres from "../components/HighhScoreres";
import StatProperties from "../components/StatProperties";
import styles from "./Statistics.module.css";
import PieChart from "../components/PieChart";
import { useEffect, useState } from "react";
import { socket } from "../socket";
import Constants from "../Constants";
import Loader from "../components/Loader";

const Statistics = () => {
  const [wrongAns, setWrongAns] = useState(0);
  const [avgAnsTime, setAvgAnsTime] = useState(0);
  const [gamesPlayed, setGamesPlayed] = useState(0);
  const [highScore, setHighScore] = useState(0);
  const [rightAns, setRightAns] = useState(0);

  const [isLoading, setIsLoading] = useState(true);
  const [errorInPersonal, setErrorInPersonal] = useState(false);

  useEffect (() => {  
    socket.on("getPersonalStatsResponse", (response) => {
      if (response.status === Constants.WORK_STATUS) {
        console.log("avg: ", response["statistics"][Constants.FIELDS.AVERAGE_ANSWER_TIME])
        setAvgAnsTime(response["statistics"][Constants.FIELDS.AVERAGE_ANSWER_TIME])
        setGamesPlayed(response["statistics"][Constants.FIELDS.GAMES_PLAYED])
        setHighScore(response["statistics"][Constants.FIELDS.HIGH_SCORE])
        setRightAns(response["statistics"][Constants.FIELDS.CORRECT_ANSWER_COUNT])
        setWrongAns(response["statistics"][Constants.FIELDS.WRONG_ANSWER_COUNT])
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
      socket.off("getPersonalStatsResponse")
    )
  }, [])
  
  return (
    <div className={styles.statistics}>
      <section className={styles.highhScoreresParent}>
        <HighhScoreres />
         {isLoading ? <Loader /> :
         errorInPersonal ? <p>The user havent played any games </p> :
         <PieChart 
            correctAns={rightAns}
            wrongAns={wrongAns}
         />
         }
      </section>
      {isLoading ? <Loader /> :
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
