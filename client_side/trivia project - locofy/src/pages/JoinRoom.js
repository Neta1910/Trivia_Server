import { useEffect, useState } from "react";
import RoomCard from "../components/RoomCard1";
import styles from "./JoinRoom.module.css";
import { socket } from "../socket";
import Constents from "../Constants";

const JoinRoom = () => {
  const [isLoading, setIsLoading] = useState(true);
  const [rooms, setRooms] = useState([]);
  const [error, setError] = useState("");

  useEffect(() => {
    const intervalRoons = setInterval(() => {
      socket.emit("getRooms");
    }, 3000); // 3 seconds interval

    socket.on("getRoomsResponse", (response) => {
      if (response.status === Constents.WORK_STATUS) {
        setRooms(response.rooms);
        setIsLoading(false);
      }
      else if (response.status === Constents.FAILED_STATUS) {
        setError("Error while recieving ");
        setIsLoading(false);
      }
    });
  
    socket.on("roomAdded", (response) => {
      setRooms(...rooms, response.room);
    })
    
    return (
      () => {
        socket.off("getRoomsResponse");
        socket.off("roomAdded")
        clearInterval(intervalRoons)
      }
    )
  }, []);

  if (isLoading) return <p>Loading elemnts </p>;
  if (error.length > 0) return <p> An error accured while loading </p>
  if (rooms.length === 0) return <p>There are no rooms</p>
  
  return (
    <div className={styles.joinRoom}>
      <section className={styles.frameParent}>
        <div className={styles.frameWrapper}>
          <div className={styles.frameGroup}>
            <div className={styles.chooseARoomWrapper}>
              <div className={styles.chooseARoom}>choose a room</div>
            </div>
            <div className={styles.roomCardParent}>
              {rooms.map((room) => (
                <RoomCard 
                  RoomName={room[Constents.FIELDS.ROOM_NAME]} 
                  AmountOfPlayers={room[Constents.FIELDS.MAX_USERS]}
                  timeout={room[Constents.FIELDS.ANSOWER_TIMEOUT]}
                  questions={room[Constents.FIELDS.QUESTION_COUNT]}
                  roomId={room[Constents.FIELDS.ROOM_ID]}
                />
              ))}
            </div>
          </div>
        </div>
      </section>
    </div>
  );
};

export default JoinRoom;
