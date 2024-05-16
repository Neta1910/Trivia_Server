import React, { useState } from 'react';
import { useSocket } from '../componenets/socketContext';
import styles from '../styles/CreateRoom.module.css';
import Constants from '../constents'
import { useRouter } from 'next/router';
const CreateRoom = () => {
    const [roomName, setRoomName] = useState('');
    const [timePerQuestion, setTimePerQuestion] = useState(0);
    const [maxPlayers, setMaxPlayers] = useState(0);
    const [questionCount, setQuestionCount] = useState(0);
    const [roomId, setRoomId] = useState(0)
    const socket = useSocket();
    const router = useRouter();
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
                console.log(response, response.roomId, roomId);
                router.push({
                    pathname: '/rooms/[roomId]', // Make sure this matches your file name in the pages directory
                    query: { roomId: response.roomId } // Replace 'desired-room-id' with the actual room ID you want to navigate to.
                });

            } else {
                alert('somthing went wrong');
            }
        }
        );
        return () => {
            socket.off('createRoomResponse');
        };
    }
    

    return (
        <div className={styles.container}>
            <form onSubmit={handleSubmit} className={styles.form}>
                <div>
                    <label htmlFor="roomName">Room Name:</label>
                    <input
                        id="roomName"
                        type="text"
                        value={roomName}
                        onChange={(e) => setRoomName(e.target.value)}
                        className={styles.input}
                    />
                </div>
                <div>
                    <label htmlFor="questionTime">Question Time (seconds):</label>
                    <input
                        id="questionTime"
                        type="number"
                        value={timePerQuestion}
                        onChange={(e) => setTimePerQuestion(e.target.value)}
                        className={styles.input}
                    />
                </div>
                <div>
                    <label htmlFor="maxPlayers">Max Players:</label>
                    <input
                        id="maxPlayers"
                        type="number"
                        value={maxPlayers}
                        onChange={(e) => setMaxPlayers(e.target.value)}
                        className={styles.input}
                    />
                </div>

                <div>
                    <label htmlFor="questionCount">question Count:</label>
                    <input
                        id="QuestionCount"
                        type="number"
                        value={questionCount}
                        onChange={(e) => setQuestionCount(e.target.value)}
                        className={styles.input}
                    />
                </div>
                <button type="submit" className={styles.button}>Create Room</button>
            </form>
        </div>
    );
};

export default CreateRoom;