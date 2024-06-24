import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react-swc'
import { ViteCspPlugin} from 'vite-plugin-csp'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    react(),
    ViteCspPlugin({
      policies: {
        'default-src': ["'self'"],
        'script-src': ["'self'", "'unsafe-inline'"],
        'style-src': ["'self'", "'unsafe-inline'"],
      },
    }),
  ],
});
