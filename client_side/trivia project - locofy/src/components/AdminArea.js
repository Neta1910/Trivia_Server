import HighhScoreres from "./HighhScoreres";
import styles from "./AdminArea.module.css";

const AdminArea = () => {
  return (
    <section className={styles.adminArea}>
      <HighhScoreres />
      <div className={styles.actionSectionAdminWrapper}>
        <div className={styles.actionSectionAdmin}>
          <div className={styles.adminButton}>
            <div className={styles.everyoneIsWaitingContainer}>
              <p className={styles.everyoneIsWaiting}>everyone is waiting,</p>
              <p className={styles.startTheGame}>start the game</p>
            </div>
          </div>
          <div className={styles.adminButton1}>
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
