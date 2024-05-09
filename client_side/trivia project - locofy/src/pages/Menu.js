import MenuBarIcon from "../components/MenuBarIcon";
import styles from "./Menu.module.css";

const Menu = () => {
  return (
    <div className={styles.menu}>
      <div className={styles.frameParent}>
        <div className={styles.frameGroup}>
          <div className={styles.createRoomWrapper}>
            <div className={styles.createRoom}>Create room</div>
          </div>
          <div className={styles.joinRoomWrapper}>
            <div className={styles.joinRoom}>Join room</div>
          </div>
        </div>
        <div className={styles.frameContainer}>
          <div className={styles.vectorWrapper}>
            <img
              className={styles.frameChild}
              loading="lazy"
              alt=""
              src="/vector-3.svg"
            />
          </div>
          <div className={styles.frameDiv}>
            <div className={styles.statisticsWrapper}>
              <div className={styles.statistics}>Statistics</div>
            </div>
            <div className={styles.logOutWrapper}>
              <div className={styles.statistics}>{`Log - out `}</div>
            </div>
          </div>
        </div>
      </div>
      <div className={styles.menuInner}>
        <img
          className={styles.frameItem}
          loading="lazy"
          alt=""
          src="/vector-4.svg"
        />
      </div>
      <MenuBarIcon menuBar="/menu-bar.svg" />
    </div>
  );
};

export default Menu;
