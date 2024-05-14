import styles from "./HighhScoreres1.module.css";
import PlayerInHigh from "./PlayerInHigh";

const ListOfPlayers = ({ players }) => {
  return (
    <div className={styles.highhScoreres}>
      {players.length === 0 ? (
        <p>There are no players in this room yet</p>
      ) : (
        players.map((elemnt, index) => {
          <PlayerInHigh
            userName={elemnt[Constents.FIELDS.USER_NAME]}
            place={index}
            isInHigh={false}
          />;
        })
      )}
    </div>
  );
};

export default ListOfPlayers;
