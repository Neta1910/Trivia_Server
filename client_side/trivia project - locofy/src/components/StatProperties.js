import UserStats from "./UserStats";
import styles from "./StatProperties.module.css";

const StatProperties = ({numOfGames, highScore, avgTime}) => {
  return (
    <section className={styles.userStatsParent}>
        <UserStats
          nameStat={`you played ${numOfGames} games`} // Correctly formatted prop
          icon={"/fluentgames24filled.svg"}
        />

        <UserStats
          icon="/fluentgames24filled-1.svg"
          background="linear-gradient(91.65deg, #ffee88, #06bee1)"
          nameStat={`your rating is ${highScore}`}
        />
        
        <UserStats
          icon="/tableralarmaverage.svg"
          background="linear-gradient(91.65deg, #ffee88, #06bee1)"
          nameStat={`your avg time is ${avgTime} seconds`}
        /> 
    </section>
  );
};

export default StatProperties;
