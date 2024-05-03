import { useRouter } from 'next/router';
import Head from 'next/head';
import Link from 'next/link';

export default function Home() {
  const router = useRouter();

  // Function to navigate programmatically
  const navigateToAbout = () => {
    router.push('login');
  };

  return (
    <>
      <Head>
        <title>Home Page</title>
      </Head>
      <div>
        <h1>Welcome to the Home Page</h1>
        <p>Current path: {router.pathname}</p>
        <button onClick={navigateToAbout}>Go to About Page</button>
      </div>
    </>
  );
}