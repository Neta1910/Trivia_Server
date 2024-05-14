import TopPart from "../components/FrameComponent1";
import AdminArea from "../components/AdminArea";
import styles from "./WaitRoom.module.css";
import { useSearchParams } from 'react-router-dom';
import { useEffect, useState } from "react";
import { socket } from "../socket";
import Constants from "../Constants";
import ActionSectionNotAdmin from '../components/ActionSectionNotAdmin'
import ListOfPlayers from "../components/HighhScoreres1";

const WaitRoom = () => {
  const [searchParams] = useSearchParams();
  const roomId = searchParams.get('roomId');
  const [isAdmin, setIsAdmin] = useState(false);
  const [isLoadingAdmin, setIsLoadingAmIAdmin] = useState(true);

  const [error, setError] = useState(false);
  const [questions, setQuestions] = useState(0);
  const [timeOut, setTimeOut] = useState(0);
  const [isLoadingStat, setIsLoadingStat] = useState(true);

  const [players, setPlayers] = useState([]);
  

  useEffect(() => {
    socket.on ('amIAdminResponse', (response) => {
      if (response.status === Constants.WORK_STATUS) {
        setIsAdmin(response.state);
        setIsLoadingAmIAdmin(false);
      }
      else {
        setError(true);
        setIsLoadingStat(false);
      }
    })

    socket.on('getRoomStateResponse', (response) => {
      if (response.status === Constants.WORK_STATUS) {
        setTimeOut(response.answerTimeout);
        setQuestions(response.questionCount);
        setPlayers(response.players);
        setIsLoadingStat(false);
      }
      else {
        setError(true);
        setIsLoadingStat(false);
      }
    })


    socket.on ("getPlayersInRoomResponse", (response) => {
      if (response.status === Constants.WORK_STATUS) {
        setPlayers(response.players);
      }
      else {
        setError(true);
      }
    })

    socket.emit("AmIAdmin");
    
    socket.emit("getRoomState")


    return () => {
      // Clean up the event listeners when the component unmounts
      socket.off('amIAdminResponse', handleAmIAdminResponse);
      socket.off('getRoomStateResponse', handleGetRoomStateResponse);
      socket.off("getPlayersInRoomResponse", handleGetPlayersInRoomResponse);
    };
  }, [socket])

  // if (isLoading) return <p>Still loading data </p>
  // if (error) return <p>There is an error</p>

  return (
    <div className={styles.mainContainer} >
      <div className={styles.waitRoom}>
        <TopPart 
          timout={timeOut}
          amountOfQuestions={questions}
        />
      <section className={styles.adminArea}>
        <ListOfPlayers 
          players={players}
        />
        {isAdmin ? <AdminArea /> : <ActionSectionNotAdmin />}
      </section>
      </div>
    </div>
  );
};

export default WaitRoom;
