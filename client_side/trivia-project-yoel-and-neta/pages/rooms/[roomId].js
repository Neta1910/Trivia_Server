import { useRouter } from "next/router";
import { useEffect, useState } from "react";
import { useSocket } from "../../componenets/socketContext";
import Player from "../../componenets/Player";
import QuestionCount from "../../componenets/QuestionCount";
import AnswerTimeout from "../../componenets/ansowerTimeout";
import Constants from "../../constents";
import styles from "../../styles/Button.module.css";

export default function Room() {
  const router = useRouter();
  const { roomId } = router.query;
  const [players, setPlayers] = useState([]);
  const [gameBegun, setGameBegun] = useState(false);
  const [questionCount, setQuestionCount] = useState(0);
  const [answerTimeout, setAnswerTimeout] = useState(0);
  const [isAdmin, setIsAdmin] = useState(false);
  const socket = useSocket();

  useEffect(() => {
    if (!socket) return;
    console.log("room_id in room: ", roomId)
    // socket.emit("getPlayersInRoom", { roomId: roomId });
    socket.emit('getRoomState');
    socket.emit('AmIAdmin');

    // socket.on("getPlayersInRoomResponse", (response) => {
    //   console.log("players", response);
    //   if (response.status === Constants.WORK_STATUS) {
    //     console.log("Players: ", response.players);
    //     setPlayers(response.players);
    //   } else {
    //     alert("Something went wrong - get players");
    //   }
    // });

    socket.on("getRoomStateResponse", (response) => {
      if (response.status === Constants.WORK_STATUS) {
        console.log("stats: ", response);
        setGameBegun(response.hasGameBegun);
        setQuestionCount(response.questionCount);
        setAnswerTimeout(response.answerTimeout);
        setPlayers(response.players)
      } else {
        alert("Something went wrong - get stat");
      }
    });

    socket.on("amIAdminResponse", (response) => {
      console.log("User is admin: ", response.state);
      setIsAdmin(response.state);
    });

    return () => {
      socket.off("getPlayersInRoomResponse");
      socket.off("getRoomStateResponse");
      socket.off("amIAdminResponse");
    };
  }, [socket, roomId]);

  function leaveRoom() {
    socket.emit("LeaveRoom", { roomId: roomId });
    router.push("/"); // Redirect to homepage or another route
  }

  function deleteRoom() {
    socket.emit("closeRoom", { roomId: roomId });
    router.push("/"); // Redirect after deletion
  }

  function startGame() {
    socket.emit("startGame");
  }

  return (
    <div>
      <h1>Room: {roomId}</h1>
      {gameBegun ? (
        <p>The game has begun!</p>
      ) : (
        <p>Waiting for game to start...</p>
      )}
      {isAdmin && (
        <div>
          <button
            onClick={startGame}
            className={`${styles.button} ${styles.adminButton}`}
          >
            Start Game
          </button>
          <button
            onClick={deleteRoom}
            className={`${styles.button} ${styles.adminButton}`}
          >
            Delete Room
          </button>
        </div>
      )}
      <QuestionCount count={questionCount} />
      <AnswerTimeout timeout={answerTimeout} />
      <ul>
        {players.map((player, index) => (
          <Player key={index} name={player} />
        ))}
      </ul>
      <button
        onClick={leaveRoom}
        className={`${styles.button} ${styles.leaveButton}`}
      >
        Leave Room
      </button>
    </div>
  );
}
