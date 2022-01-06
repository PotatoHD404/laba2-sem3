<script>
  export let label_text;
  export let svg;
</script>
<div class='flex my-2 w-full md:w-2/3 pt-1 pb-20'>
  <div id='graph' class='relative input-component empty w-full h-8 px-1'>
    <label class='absolute left-2 transition-all px-1 bg-transparent dark:text-gray-200 select-none'>
      {label_text}
    </label>
    {@html svg}
  </div>
</div>
<style>
    label {
        pointer-events: none;
        color: rgba(70, 70, 70, 1);
        top: 0;
        transform: translateY(-100%);
        font-size: 11px;
    }
</style>