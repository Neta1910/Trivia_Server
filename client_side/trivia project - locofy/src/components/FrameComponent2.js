import RoomCard1 from "./RoomCard1";
import styles from "./FrameComponent2.module.css";

const FrameComponent2 = () => {
  return (
    <div className={styles.frameWrapper}>
      <div className={styles.frameParent}>
        <div className={styles.chooseARoomWrapper}>
          <div className={styles.chooseARoom}>choose a room</div>
        </div>
        <RoomCard1 />
      </div>
    </div>
  );
};

export default FrameComponent2;
