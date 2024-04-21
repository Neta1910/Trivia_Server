import { useRouter } from 'next/router';
import { useEffect, useState } from 'react';
import { useSocket } from '../../components/socketContext';  // Ensure the path is correct
import Player from '../../components/Player';  // Corrected the typo in 'components'
import QuestionCount from '../../componenets/QuestionCount';
import AnswerTimeout from '../../componenets/ansowerTimeout';

export default function Room() {
    const router = useRouter();
    const { roomId } = router.query;
    const [players, setPlayers] = useState([]);
    const [gameBegun, setGameBegun] = useState(false);
    const [questionCount, setQuestionCount] = useState(0);
    const [answerTimeout, setAnswerTimeout] = useState(0);
    const socket = useSocket();

    useEffect(() => {
        if (!socket) return;

        // Emit to get the initial state of the room
        socket.emit('getPlayersInRoom', { roomId });
        socket.emit('getRoomState', { roomId });

        // Handle response for players in room
        socket.on('getPlayersInRoomResponse', (response) => {
            if (response.status === 'WORK_STATUS') { 
                setPlayers(response.players);
            } else {
                alert('Something went wrong');
            }
        });

        // Handle response for room state
        socket.on('getRoomStateResponse', (response) => {
            if (response.status === 'WORK_STATUS') {
                setGameBegun(response.hasGameBegun);
                setPlayers(response.players);  // Update players list if it's part of this response
                setQuestionCount(response.questionCount);
                setAnswerTimeout(response.answerTimeout);
            } else {
                alert('Something went wrong');
            }
        });

        // Cleanup the effect to avoid memory leaks and multiple listeners
        return () => {
            socket.off('getPlayersInRoomResponse');
            socket.off('getRoomStateResponse');
        };
    }, [socket, roomId]);

    return (
        <div>
            <h1>Room: {roomId}</h1>
            {gameBegun ? <p>The game has begun!</p> : <p>Waiting for game to start...</p>}
            <QuestionCount count={questionCount} />
            <AnswerTimeout timeout={answerTimeout} />
            <ul>
                {players.map((player, index) => (
                    <Player key={index} name={player} />
                ))}
            </ul>
        </div>
    );
}
