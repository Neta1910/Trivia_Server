import styles from "./HighhScoreres1.module.css";
import PlayerInHigh from "./PlayerInHigh";
import Constants from "../Constants";
import { layouts } from "chart.js";

const ListOfPlayers = ({ players }) => {
  return (
    <div className={styles.highhScoreres}>
      {players.length === 0 ? (
        <p>There are no players in this room yet</p>
      ) : (
        players.map((element, index) => (
          <PlayerInHigh
            key={index}
            userName={element}
            place={index + 1}
            isInHigh={false}
          />
        ))
      )}
    </div>
  );
};

export default ListOfPlayers;
