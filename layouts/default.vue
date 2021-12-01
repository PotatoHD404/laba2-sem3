<template>
  <Header/>
  <Nuxt/>
</template>


<script>
import Header from '../components/header.vue';
import '../app.postcss';

const site_name = 'PotatoHD website';
const description = 'Lab 1 sem 3 that can sort your data';

export default {
  data() {
    return {
      title: 'Home page'
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
        }
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
</style>