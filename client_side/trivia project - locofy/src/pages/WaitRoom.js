import FrameComponent1 from "../components/FrameComponent1";
import AdminArea from "../components/AdminArea";
import styles from "./WaitRoom.module.css";

const WaitRoom = () => {
  return (
    <div className={styles.waitRoom}>
      <FrameComponent1 />
      <AdminArea />
    </div>
  );
};

export default WaitRoom;
