const colors = require('tailwindcss/colors');

const config = {
  mode: 'jit',
  darkMode: 'class',
  purge: [
    './src/**/*.{html,scripts,svelte,ts}'
  ],
  variants: {
    extend: {
      textOpacity: ['dark']
    }
  },
  theme: {
    extend: {},
    colors: {
      transparent: 'transparent',
      current: 'currentColor',
      black: colors.black,
      white: colors.white,
      gray: colors.gray,
      indigo: colors.indigo,
      red: colors.rose,
      yellow: colors.amber,
      'dark': '#0d1117',
      'alt-dark': '#21262d',
      'outline-dark': '#373b42',
      'dark-text': '#c9d1d9',
      'light-text': '#24292f',
      'deep-black': '#010409',
      'light': '#f5f6f8',
      'outline-light': '#d5d5d8'


    }
  },
  plugins: []
};

module.exports = config;
