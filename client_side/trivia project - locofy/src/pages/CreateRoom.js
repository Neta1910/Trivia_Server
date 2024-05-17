import MenuBarIcon from "../components/MenuBarIcon";
import styles from "./CreateRoom.module.css";
import TextInput from "../components/UserNameInput";
import { socket } from "../socket";
import { useNavigate } from "react-router-dom";
import { useEffect } from "react";

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
    // Listen for the login response from the server
    socket.on('createRoomResponse', (response) => {
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
  }

  useEffect (() => {
    socket.on("createRoomResponse", )
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

              />
              {/* <button className={styles.roomNameParent}>
                <div className={styles.roomName}>Room name</div>
                <div className={styles.frameWrapper}>
                  <div className={styles.vectorParent}>
                    <img
                      className={styles.frameItem}
                      alt=""
                      src="/vector-2.svg"
                    />
                    <img
                      className={styles.wpfnameIcon}
                      alt=""
                      src="/wpfname.svg"
                    />
                  </div>
                </div>
              </button> */}
              <div className={styles.questionTimeOutQuestionParent}>
                <button className={styles.questionTimeOutQuestion}>
                  <div className={styles.questionTimeout}>Question timeOut</div>
                  <div className={styles.questionTimeOutQuestionInner}>
                    <div className={styles.mingcutetimeFillParent}>
                      <img
                        className={styles.mingcutetimeFillIcon}
                        alt=""
                        src="/mingcutetimefill.svg"
                      />
                      <img
                        className={styles.frameItem}
                        alt=""
                        src="/vector-2.svg"
                      />
                    </div>
                  </div>
                </button>
                <button className={styles.questionTimeOutQuestion1}>
                  <div className={styles.questionTimeout}>
                    Amount of players
                  </div>
                  <div className={styles.frameParent}>
                    <div className={styles.vectorWrapper}>
                      <img
                        className={styles.vectorIcon}
                        alt=""
                        src="/vector-2.svg"
                      />
                    </div>
                    <img
                      className={styles.gameIconstabletopPlayers}
                      alt=""
                      src="/gameiconstabletopplayers.svg"
                    />
                  </div>
                </button>
              </div>
              <div className={styles.menuBarWrapper}>
                <button className={styles.menuBar}>
                  <div className={styles.questionCount}>Question count</div>
                  <div className={styles.menuBarInner}>
                    <div className={styles.vectorGroup}>
                      <img
                        className={styles.frameItem}
                        alt=""
                        src="/vector-2.svg"
                      />
                      <img
                        className={styles.pajamasquestionIcon}
                        alt=""
                        src="/pajamasquestion.svg"
                      />
                    </div>
                  </div>
                </button>
              </div>
              <div className={styles.fRAMEInner}>
                <button className={styles.submitWrapper}>
                  <div className={styles.submit}>Submit</div>
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
