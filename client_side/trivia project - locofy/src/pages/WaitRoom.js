import TopPart from "../components/FrameComponent1";
import AdminArea from "../components/AdminArea";
import styles from "./WaitRoom.module.css";
import { useNavigate } from 'react-router-dom';
import { useEffect, useState } from "react";
import { socket } from "../socket";
import Constants from "../Constants";
import ActionSectionNotAdmin from '../components/ActionSectionNotAdmin';
import ListOfPlayers from "../components/HighhScoreres1";
import Loader from "../components/Loader";

const WaitRoom = () => {
  const [isAdmin, setIsAdmin] = useState(false);
  const [error, setError] = useState(false);
  const [questions, setQuestions] = useState(0);
  const [timeOut, setTimeOut] = useState(0);
  const [isGameActive, setIsGameActive] = useState(false)
  const [isLoadingStat, setIsLoadingStat] = useState(true);
  
  const roomId = localStorage.getItem("currentRoomId");
  const [players, setPlayers] = useState([]);
  const navigate = useNavigate();

  useEffect(() => {
    const handleAmIAdminResponse = (response) => {
      if (response.status === Constants.WORK_STATUS) {
        setIsAdmin(response.state);
      } else {
        setError(true);
      }
    };

    const handleGetRoomStateResponse = (response) => {
      if (response.status === Constants.WORK_STATUS) {
        console.log(response)
        setTimeOut(response.answerTimeout);
        setQuestions(response.questionCount);
        setPlayers(response.players);
        setIsGameActive(response.hasGameBegun)
        if (response.hasGameBegun) {
          navigate("/game-board")
        }
        setIsLoadingStat(false);
      } else if (response.status === Constants.FAILED_STATUS) {
        setError(true);
        setIsLoadingStat(false);
      }
    };

    const handleGetPlayersInRoomResponse = (response) => {
      if (response.status === Constants.WORK_STATUS) {
        setPlayers(response.players);
      } else {
        setError(true);
      }
    };

    const handleStartGameResponse = (response) => {
      if (response.status === Constants.WORK_STATUS) {
        navigate(`/game-board?answerTimeout=${timeOut}`);
      } else {
        console.log("error");
      }
    };

    const handleCloseRoomResponse = (response) => {
      if (response.status === Constants.WORK_STATUS) {
        if (!isAdmin) {
          alert("The admin has closed the room");
        }
        navigate("/menu");
      }
    };

    socket.on('amIAdminResponse', handleAmIAdminResponse);
    socket.on('getRoomStateResponse', handleGetRoomStateResponse);
    socket.on('getPlayersInRoomResponse', handleGetPlayersInRoomResponse);
    socket.on('startGameResponse', handleStartGameResponse);
    socket.on('closeRoomResponse', handleCloseRoomResponse);

    const intervalGame = setInterval(() => {
      if (!isGameActive) {
        socket.emit("getRoomState");
      }
    }, 3000); // 3 seconds interval

    socket.emit("AmIAdmin");

    return () => {
      socket.off('amIAdminResponse', handleAmIAdminResponse);
      socket.off('getRoomStateResponse', handleGetRoomStateResponse);
      socket.off('getPlayersInRoomResponse', handleGetPlayersInRoomResponse);
      socket.off('startGameResponse', handleStartGameResponse);
      socket.off('closeRoomResponse', handleCloseRoomResponse);
      clearInterval(intervalGame)
    };
  }, [socket, navigate, isAdmin, isGameActive]);
  console.log('timeout', timeOut)
  
  if (error) return <p>There is an error</p>;
  if (isLoadingStat) return <Loader />

  return (
    <div className={styles.mainContainer}>
      <div className={styles.waitRoom}>
        <TopPart 
          timeout={timeOut}
          amountOfQuestions={questions}
        />
        <section className={styles.adminArea}>
          <ListOfPlayers 
            players={players}
          />
          {isAdmin ? <AdminArea roomId={roomId} timeOut={timeOut}/> : <ActionSectionNotAdmin />}
        </section>
      </div>
    </div>
  );
};

export default WaitRoom;
