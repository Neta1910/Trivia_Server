import io from 'socket.io-client';

// Assuming your server is running on this URL
const SOCKET_URL = 'http://localhost:3000';

const socket = io(SOCKET_URL, {
  transports: ['websocket'], // use WebSocket first, fallback to HTTP long-polling
  upgrade: false,
});

export default socket;