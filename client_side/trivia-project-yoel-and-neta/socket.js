import io from 'socket.io-client';

// Assuming your server is running on this URL
const SOCKET_URL = 'http://127.0.0.1:5000';

const socket = io(SOCKET_URL, {
  reconnection: false, // Enable reconnection
  reconnectionAttempts: 100, // Maximum number of reconnection attempts
  reconnectionDelay: 1000, // Delay between each reconnection attempt (in milliseconds)
});

export default socket;