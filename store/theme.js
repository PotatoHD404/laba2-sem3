export const state = () => ({
    dark: true
})

export const mutations = {
    toggle(state) {
        state.dark = !state.dark;
        document.body.classList.remove('light');
        document.body.classList.remove('dark');
        const value = state.dark ? 'dark' : 'light';
        document.body.classList.add(value);
        if(process.client) {
            localStorage.setItem('theme', value);
        }
    },
}