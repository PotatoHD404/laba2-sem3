<template>
  <nav class='flex items-center justify-between flex-wrap bg-teal-500 p-6'>
    <div class='flex items-center flex-shrink-0 text-white mr-6'>
      <img src='/favicon.png' alt='Beautiful image' class='w-10 mr-2'>
      <span class='font-semibold text-xl tracking-tight text-black dark:text-white'>
      PotatoHD's lab
    </span>
    </div>
    <div class='block'>
      <button type='button' class='p-2 transition bg-light border border-transparent
     rounded-md focus:outline-none 0 ring-1 ring-outline-light dark:ring-outline-dark
      dark:hover:ring-gray-400 duration-300 dark:duration-200 hover:bg-gray-200 dark:bg-alt-dark'
              v-on:click="() => { index = (index + 1) % themes.length; theme.set(themes[index]) }">
        {{ icons[+ dark] }}
      </button>
    </div>
  </nav>
</template>

<script>
import Input from "./input-comp";
import Select from "./select-comp";
import Field from "./field-comp";

import {mapMutations} from 'vuex'

const icons = ['🌙', '🌞'];
export default {
  beforeCreate() {
    theme.subscribe((value) => {
      if (localStorage == null || localStorage.getItem('theme') == null) {
        localStorage.setItem('theme', 'dark');
        theme.set('dark');
      } else if (value === '' && localStorage.getItem('theme') != null)
        theme.set(localStorage.getItem('theme'));
      else {
        if (value === 'light')
          index = 1;
        document.body.classList.remove('light');
        document.body.classList.remove('dark');
        document.body.classList.add(value);
        localStorage.setItem('theme', value);
      }

    });
  },
  components: {
    Input,
    Select,
    Field
  },
  computed: {
    todos() {
      return this.$store.state.theme.dark
    }
  },
  methods: {
    ...mapMutations({
      toggle: 'theme/toggle'
    })
  }
}
</script>