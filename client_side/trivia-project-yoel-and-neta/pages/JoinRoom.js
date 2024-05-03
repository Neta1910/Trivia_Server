import { useEffect, useState } from "react";
import RoomCard from "../componenets/roomCard";
import { useSocket } from '../componenets/socketContext'
import LoadingBar from "../componenets/loadingData";
import Constants from '../constents'

const JoinRoom = () => {
    const [rooms, setRooms] = useState([]);
    const [loading, setLoading] = useState(true); // Track loading state
    const [error, setError] = useState(null); // Track error state
    const socket = useSocket();

    useEffect(() => {
        socket.emit("getRooms")

        // Listen for the login response from the server
        socket.on('getRoomsResponse', (response) => {
            if (response.status === Constants.WORK_STATUS) {
                setLoading(false);
                setRooms(JSON.parse(response.rooms));
            } else {
                setLoading(false);
                setError("Error getting from server... ");
            }

                // Listen for the login response from the server
        socket.on('roomDeleted', (response) => {
            setRooms(currentRooms => currentRooms.filter(room => room.id !== response.roomId));
        });

        socket.on('roomAdded', (response) => {
            setRooms(rooms.push(JSON.parse(response.room)));
        });

        // Clean up on component unmount
        return () => {
            socket.off('getRoomsResponse')
            socket.off('roomAdded')
            socket.off('roomDeleted')
        };
    }, [])})

    if (loading) return <LoadingBar />
    if (rooms.length == 0) return <p> There is no aveilable rooms </p>

    return (
        <div>
            {rooms.map((room, index) => (
                <RoomCard
                    key={index}
                    roomId={room.roomId}
                    roomName={room.roomName}
                    maxPlayers={room.maxPlayers}
                    numOfQuestionsInGame={room.numOfQuestionsInGame}
                    timePerQuestion={room.timePerQuestion}
                    isActive={room.isActive}
                />
            ))}
        </div>
    )
}

export default JoinRoom;