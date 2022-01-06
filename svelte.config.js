import preprocess from "svelte-preprocess";
import vercel from '@sveltejs/adapter-vercel';

const config = {
  kit: {
    adapter: vercel(),
    target: '#svelte',
  },
  vite: {
    optimizeDeps: {
      exclude: ['svelte-kit-cookie-session'],
    },
  },
  preprocess: [preprocess({
    "postcss": true
  })]
};

export default config;
