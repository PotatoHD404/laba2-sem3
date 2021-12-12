<script>
  import Header from '../components/header.svelte';
  import '../app.postcss';

  const site_name = 'PotatoHD website';
  const description = 'Lab 1 sem 3 that can sort your data';
</script>
<svelte:head>
  <link rel='icon' href='/favicon.png'>
  <meta name='viewport' content='width=device-width, initial-scale=1'>
  <meta name='robots' content='follow, index'>
  <title>{site_name}</title>
  <meta content='{description}' name='description'>
  <meta property='og:title' content='{site_name}'>
  <!--  <meta property="og:image" content="/twitter.png">-->
  <!--  <meta name="twitter:card" content="summary_large_image">-->
  <meta name='twitter:title' content='{site_name}'>
  <meta name='twitter:description' content='{description}'>
  <!--  <meta name="twitter:image" content="/twitter.png">-->
</svelte:head>
<Header />
<slot></slot>

<style>
    @tailwind base;
    @tailwind components;
    @tailwind utilities;
</style>