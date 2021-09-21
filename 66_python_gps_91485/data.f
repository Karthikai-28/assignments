      implicit double precision (a - h, o - z)
      dimension          u(3),        v(3)
      open (unit = 20, file = 'data.dat')
      open (unit = 21, file = 'data.sht')
      pi = 2.0d0*dacos(0.0d0)
      write (20, 1000) pi
      write (21, 1000) pi
      c = 2.99792458d08
      write (20, 1010) c
      write (21, 1010) c
      r = 6.3674445d6
      write (20, 1020) r
      write (21, 1020) r
      s = 8.616409d04
      write (20, 1030) s
      write (21, 1030) s
      v(1) = 0.0d0
      v(3) = dsin(55.0d0/360.0d0*2.0d0*pi)
      v(2) = dsqrt(1.0d0 - v(3)**2)
      u(1) = 1.0d0
      u(2) = 0.0d0
      u(3) = 0.0d0
      h = 2.0200d7
      p = s/2.0d0
*
      do 40 i = 1, 6
         do 30 j = 1, 4
            isat = (i - 1)*4 + j-1
            do 10 k = 1, 3
               write (20, 1040) u(k), k, isat
               if (isat .eq. 0) write (21, 1040) u(k), k, isat
   10       continue
            do 20 k = 1, 3
               write (20, 1050) v(k), k, isat
               if (isat .eq. 0) write (21, 1050) v(k), k, isat
   20       continue
            write (20, 1070) p, isat
            write (20, 1080) h, isat
            phase = dfloat(i - 1) + dfloat(j - 1)*pi/2.0d0 
            write (20, 1090) phase, isat
            if (isat .eq. 1) then
               write (21, 1070) p, isat
               write (21, 1080) h, isat
               write (21, 1090) phase, isat
            end if   
   30    continue
         if (i .lt. 6) then
            u1 = u(1)/2.0d0 - dsqrt(0.75d0)*u(2)
            u2 = dsqrt(0.75d0)*u(1) + u(2)/2.0d0
            u(1) = u1
            u(2) = u2
            v1 = v(1)/2.0d0 - dsqrt(0.75d0)*v(2)
            v2 = dsqrt(0.75d0)*v(1) + v(2)/2.0d0
            v(1) = v1
            v(2) = v2
         end if
   40 continue
      close (20)
      close (21)
      stop
 1000 format (1pd26.18, 10x, ' /= pi ')
 1010 format (1pd26.18, 10x, ' /= c, speed of light, [m/s] ')
 1020 format (1pd26.18, 10x, ' /= R, radius of earth, [m] ')
 1030 format (1pd26.18, 10x, ' /= s, length of a sidereal day, [s]')
 1040 format (1pd26.18, 10x, ' /= u', i1, ' of Sat. ', i2)
 1050 format (1pd26.18, 10x, ' /= v', i1, ' of Sat. ', i2)
 1060 format (' check: plane ', i2, ' satellite ', i4, 2(' 1 = ', f4.2),
     +   ' 0 /= ', d12.4)
 1070 format (1pd26.18, 10x, ' /= periodicity of Sat. ', i2, ' [s]')
 1080 format (1pd26.18, 10x, ' /= altitude of Sat. ', i2, ' [m]')
 1090 format (1pd26.18, 10x, ' /= phase of Sat. ', i2, ' [rad]')
      end
