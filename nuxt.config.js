export default {
    // Target: https://go.nuxtjs.dev/config-target
    target: 'static',

    // Global page headers: https://go.nuxtjs.dev/config-head
    head: {
        title: 'laba2-sem3',
        meta: [
            {charset: 'utf-8'},
            {name: 'viewport', content: 'width=device-width, initial-scale=1'},
            {hid: 'description', name: 'description', content: ''},
            {name: 'format-detection', content: 'telephone=no'}
        ],
        link: [
            {rel: 'icon', type: 'image/x-icon', href: '/favicon.ico'}
        ]
    },
    tailwindcss: {
        exposeConfig: true
    },

    // Global CSS: https://go.nuxtjs.dev/config-css
    css: [],

    // Plugins to run before rendering page: https://go.nuxtjs.dev/config-plugins
    plugins: [],

    // Auto import components: https://go.nuxtjs.dev/config-components
    components: true,

    // Modules for dev and build (recommended): https://go.nuxtjs.dev/config-modules
    buildModules: [
        // https://go.nuxtjs.dev/tailwindcss
        '@nuxtjs/tailwindcss',
    ],

    // Modules: https://go.nuxtjs.dev/config-modules
    modules: [
        // https://go.nuxtjs.dev/pwa
        '@nuxtjs/pwa',
    ],

    // PWA module configuration: https://go.nuxtjs.dev/pwa
    pwa: {
        icon: {
            iconSrc: './static/favicon.png'
        },
        manifest: {
            lang: 'en',
            // short_name: 'P',
            // name: 'Project',
            // start_url: '/',
            // display: 'standalone',
            // theme_color: '#00b5ad'
        },
        workbox: {
            /* workbox options */
            dev: true,
            swURL: './static/scripts/actual-service-worker.js'

        }
    },

    // Build Configuration: https://go.nuxtjs.dev/config-build
    build: {}
}
