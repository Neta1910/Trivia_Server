import { useNavigate } from "react-router-dom";
import MenuBarIcon from "../components/MenuBarIcon";
import styles from "./Menu.module.css";

const Menu = () => {
  const navigate = useNavigate();
  return (
    <div className={styles.menu}>
      <div className={styles.frameParent}>
        <div className={styles.frameGroup}>
          
          <div className={styles.createRoomWrapper}>
            <div className={styles.createRoom} onClick={() => navigate("/create-room")}>Create room</div>
          </div>

          <div className={styles.joinRoomWrapper}>
            <div className={styles.joinRoom} onClick={() => navigate("/join-room")}>Join room</div>
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
              <div className={styles.statistics} onClick={() => navigate("/statistics")}>Statistics</div>
            </div>

            <div className={styles.logOutWrapper}>
              <div className={styles.statistics} onClick={() => navigate("/logout")} >{`Log - out `}</div>
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
