import HighhScoreres1 from "./HighhScoreres1";
import styles from "./AdminArea.module.css";
import { socket } from "../socket";
import { useEffect } from "react";
import Constants from "../Constants";

const AdminArea = ({roomId}) => {
  const startGame = () => {
    socket.emit("startGame", {[Constants.FIELDS.ROOM_ID]: roomId})
  }
  const deleteRoom = () => {
    socket.emit("closeRoom", {[Constants.FIELDS.ROOM_ID]: roomId})
  }
  return (
    <section className={styles.adminArea}>
      <div className={styles.actionSectionAdminWrapper}>
        <div className={styles.actionSectionAdmin}>
          <div className={styles.adminButton} onClick={startGame} >
            <div className={styles.everyoneIsWaitingContainer} >
              <p className={styles.everyoneIsWaiting}>everyone is waiting,</p>
              <p className={styles.startTheGame}>start the game</p>
            </div>
          </div>

          <div className={styles.adminButton1} onClick={deleteRoom}>
            <button className={styles.adminButton2}>
              <div className={styles.deleteRoom}>Delete room</div>
            </button>
          </div>
        </div>
      </div>
    </section>
  );
};

export default AdminArea;
