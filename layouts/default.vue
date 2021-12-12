<template>
  <body class="dark m-auto transition-colors duration-300 dark:bg-dark">
  <div>
    <Header/>
    <Nuxt/>
  </div>
  </body>
</template>


<script>
import Header from '../components/header-comp';
import '../app.postcss';

const site_name = "PotatoHD's website";
const description = 'Lab 2 sem 3 that can win you in tic tac toe';

export default {
  components: {
    Header
  },
  data() {
    return {
      title: site_name
    }
  },
  head() {
    return {
      title: site_name,
      meta: [
        {
          name: 'viewport',
          content: 'width=device-width, initial-scale=1'
        },
        {
          name: 'robots',
          content: 'follow, index'
        },
        {
          content: description,
          name: 'description'
        },
        {
          property: 'og:title',
          content: site_name
        },
        {
          name: 'twitter:title',
          content: site_name
        },
        {
          name: 'twitter:description',
          content: description
        }
      ]
    }
  }
}
</script>


<style>
@tailwind base;
@tailwind components;
@tailwind utilities;
/*body.dark {*/
/*  @apply bg-dark m-auto;*/
/*}*/
html, body {
  @apply h-screen;
}

/*body.light {*/
/*  @apply bg-white;*/
/*}*/
</style>