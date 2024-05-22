import io from 'socket.io-client';

// Assuming your server is running on this URL
const SOCKET_URL = 'http://127.0.0.1:5000';

export const socket = io(SOCKET_URL);



