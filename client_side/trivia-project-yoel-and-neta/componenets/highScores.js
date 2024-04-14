import { useState } from 'react';
import socket from '../socket.js';

const highScores = () => {
    const [highScores, setHighScores] = useState({});

    useEffect(() => socket
}