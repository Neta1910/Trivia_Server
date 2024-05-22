import HighhScoreres1 from "./HighhScoreres1";
import styles from "./AdminArea.module.css";
import { socket } from "../socket";
import { useEffect } from "react";

const AdminArea = ({roomId}) => {
  return (
    <section className={styles.adminArea}>
      <div className={styles.actionSectionAdminWrapper}>
        <div className={styles.actionSectionAdmin}>
          <div className={styles.adminButton} onClick={() => { socket.emit('startGame', {roomId: roomId}) }} >
            <div className={styles.everyoneIsWaitingContainer}>
              <p className={styles.everyoneIsWaiting}>everyone is waiting,</p>
              <p className={styles.startTheGame}>start the game</p>
            </div>
          </div>

          <div className={styles.adminButton1} onClick={() => {socket.emit("closeRoom", {roomId: roomId})}}>
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
