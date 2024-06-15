import io from 'socket.io-client';

// Assuming your server is running on this URL
const SOCKET_URL = 'http://127.0.0.1:5000';

const socket = io(SOCKET_URL);

socket.on("error", (data) => {
    console.log(data)
    alert(data.message, "try agein");
})

export {socket}



