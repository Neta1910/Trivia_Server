import { useEffect, useState } from "react";
import RoomCard from "../componenets/roomCard";
import {useSocket} from "../componenets/socket";
const JoinRoom = () => {
    const [rooms, setRooms] = useState({});
    useEffect(() => {
        

        // Setup event listeners
        newSocket.on('connect', () => {
            console.log('Connected to socket server');
        });

        newSocket.on('data', (receivedData) => {
            console.log('Data received from server', receivedData);
            setData(receivedData);
        });

        // Fetch initial data or send a message to the server to initiate data flow
        fetch('http://yourserveraddress.com/api/data')
            .then(response => response.json())
            .then(initialData => {
                setData(initialData);
                // Emit an event if needed based on the fetched data
                newSocket.emit('init', { data: initialData });
            })
            .catch(error => console.error('Error fetching initial data:', error));

        // Clean up on component unmount
        return () => {
            newSocket.disconnect();
            console.log('Disconnected from socket server');
        };
    }, []);
}