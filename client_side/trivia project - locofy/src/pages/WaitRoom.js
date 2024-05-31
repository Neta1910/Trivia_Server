import TopPart from "../components/FrameComponent1";
import AdminArea from "../components/AdminArea";
import styles from "./WaitRoom.module.css";
import { useNavigate } from 'react-router-dom';
import { useEffect, useState } from "react";
import { socket } from "../socket";
import Constants from "../Constants";
import ActionSectionNotAdmin from '../components/ActionSectionNotAdmin';
import ListOfPlayers from "../components/HighhScoreres1";

const WaitRoom = () => {
  const [isAdmin, setIsAdmin] = useState(false);
  const [error, setError] = useState(false);
  const [questions, setQuestions] = useState(0);
  const [timeOut, setTimeOut] = useState(0);
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
        setTimeOut(response.answerTimeout);
        setQuestions(response.questionCount);
        setPlayers(response.players);
        setIsLoadingStat(false);
      } else {
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
        alert("Game starts");
        navigate("/game-board");
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

    socket.emit("AmIAdmin");
    socket.emit("getRoomState");

    return () => {
      socket.off('amIAdminResponse', handleAmIAdminResponse);
      socket.off('getRoomStateResponse', handleGetRoomStateResponse);
      socket.off('getPlayersInRoomResponse', handleGetPlayersInRoomResponse);
      socket.off('startGameResponse', handleStartGameResponse);
      socket.off('closeRoomResponse', handleCloseRoomResponse);
    };
  }, [socket, navigate, isAdmin]);

  if (error) return <p>There is an error</p>;

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
          {isAdmin ? <AdminArea roomId={roomId}/> : <ActionSectionNotAdmin />}
        </section>
      </div>
    </div>
  );
};

export default WaitRoom;
