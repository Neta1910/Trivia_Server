import { useEffect, useMemo } from "react";
import styles from "./RoomCard1.module.css";
import { useNavigate } from "react-router-dom";
import { socket } from "../socket";
import Constants from "../Constants";

const RoomCard = ({RoomName, AmountOfPlayers, timeout, questions, roomId}) => {
  
  const navigate = useNavigate();
  
  useEffect(() => {
    const queryParams = new URLSearchParams({
      roomId: roomId
    }).toString();
    socket.on("joinRoomResponse", () => {
      localStorage.setItem('currentRoomId', roomId)  
      navigate(`/WaitRoom`)
    })
  }, [])

  const onClickOnCard = () => {
    socket.emit("joinRoom", {
      [Constants.FIELDS.ROOM_ID]: roomId
    })
  }

  return (
    <div className={styles.roomCard} onClick={onClickOnCard}>
      <div className={styles.frameParent}>
        <div className={styles.roomNameWrapper}>
          <div className={styles.roomName}>{RoomName}</div>
        </div>
        <div className={styles.frameChild} />
        <div className={styles.xPlayersParent}>
          <div className={styles.xPlayers}> {AmountOfPlayers } players  </div>
          <div className={styles.frameGroup}>
            <div className={styles.horizontalAxisWrapper}>
              <img
                className={styles.horizontalAxisIcon}
                loading="lazy"
                alt=""
                src="/vector-6.svg"
              />
            </div>
            <div className={styles.xTimeoutWrapper}>
              <div className={styles.xTimeout}>{timeout} timeout</div>
            </div>
            <div className={styles.instanceOfCard}>
              <div className={styles.horizontalAxisWrapper}>
                <img
                  className={styles.horizontalAxisIcon}
                  loading="lazy"
                  alt=""
                  src="/vector-6.svg"
                />
              </div>
              <div className={styles.xPlayers}>{questions} questions</div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default RoomCard;
