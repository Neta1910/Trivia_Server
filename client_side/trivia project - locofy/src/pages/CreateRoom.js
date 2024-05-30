import MenuBarIcon from "../components/MenuBarIcon";
import styles from "./CreateRoom.module.css";
import TextInput from "../components/UserNameInput";
import { socket } from "../socket";
import { useNavigate } from "react-router-dom";
import { useEffect, useState } from "react";
import SliderInput from "../components/SlliderInput";

import Constants from "../Constants";
const CreateRoom = () => {
  const [roomName, setRoomName] = useState('');
  const [timePerQuestion, setTimePerQuestion] = useState(0);
  const [maxPlayers, setMaxPlayers] = useState(0);
  const [questionCount, setQuestionCount] = useState(0);
  const [roomId, setRoomId] = useState(0)

  const navigate = useNavigate();

  function handleSubmit(e) {
    e.preventDefault(); // Prevent the form from refreshing the page

    // Emit the login event to the server with username and password
    console.log(typeof maxPlayers);
    socket.emit('createRoom', {
        [Constants.FIELDS.ROOM_NAME]: roomName,
        [Constants.FIELDS.MAX_USERS]: maxPlayers,
        [Constants.FIELDS.ANSOWER_TIMEOUT]: timePerQuestion,
        [Constants.FIELDS.QUESTION_COUNT]: questionCount
    });
  }

  useEffect (() => {
        // Listen for the login response from the server
        socket.on('createRoomResponse', (response) => {
          console.log(response);
            if (response.status === Constants.WORK_STATUS) {
                localStorage.setItem("currentRoomId", response.roomId)
                navigate("/wait-room")
            } else {
                alert('somthing went wrong');
            }
        }
        );
        return () => {
            socket.off('createRoomResponse');
        };
  })

  return (
    <div className={styles.createRoom}>
      <div className={styles.createRoomInner}>
        <div className={styles.rectangleParent}>
          <div className={styles.frameChild} />
          <h2 className={styles.createRoom1}>Create room</h2>
          <div className={styles.fRAMEWrapper}>
            <form className={styles.fRAME}>
              
              <TextInput 
              placeHolder={"Room name"} 
              icon={"/wpfname.svg"}
              setter={setRoomName}
              />

              <TextInput
              placeHolder={"Question timeOut"}
              icon={"/mingcutetimefill.svg"}
              setter={setTimePerQuestion}
              type="range"
              min={2}
              max={100}
              />
              
              {/* <SliderInput 
                setter={setTimePerQuestion}
                min={2}
                max={100}
                title={"Question timeOut"}
              /> */}

              <TextInput
              placeHolder={"Amount of players"}
              icon={"/gameiconstabletopplayers.svg"}
              setter={setMaxPlayers}
              type="range"
              min={2}
              max={30}
              />

              <TextInput
              placeHolder={"Question count"}
              icon={"/pajamasquestion.svg"}
              setter={setQuestionCount}
              type="range"
              min={2}
              max={30}
              />

              <div className={styles.fRAMEInner}>
                <button className={styles.submitWrapper}>
                  <div className={styles.submit} onClick={handleSubmit}>Submit</div>
                </button>
              </div>
            </form>
          </div>
        </div>
      </div>
      <div className={styles.createRoomChild}>
        <img
          className={styles.frameChild2}
          loading="lazy"
          alt=""
          src="/vector-5.svg"
        />
      </div>
      <MenuBarIcon menuBar="/menu-bar1.svg" />
    </div>
  );
};

export default CreateRoom;
