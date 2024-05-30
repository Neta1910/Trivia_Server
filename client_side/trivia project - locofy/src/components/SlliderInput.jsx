import React, { useState } from 'react';
import { Box, Slider, Grid, Typography, Input } from '@mui/material';

const SliderInput = ({setter, min, max, title}) => {
    const [value, setValue] = React.useState(30);
  
    const handleSliderChange = (event, newValue) => {
      setValue(newValue);
      setter(newValue)
    };
  
    const handleInputChange = (event) => {
      setter(event.target.value === '' ? 0 : Number(event.target.value));
      setValue(event.target.value === '' ? 0 : Number(event.target.value));
    };
  
    const handleBlur = () => {
      if (value < min) {
        setValue(min);
      } else if (value > max) {
        setValue(max);
      }
    };
  
    return (
      <Box sx={{ width: 400 }}>
        <Typography id={title}         sx={{
          fontFamily: 'Kavoon', // Change the font family
          fontSize: '1rem', // Change the font size
          fontWeight: 'bold', // Change the font weight
          textAlign: 'left'
        }} gutterBottom>
          {title}
        </Typography>
        <Grid container spacing={2} alignItems="center">
          <Grid item xs>
            <Slider
              value={typeof value === 'number' ? value : 0}
              onChange={handleSliderChange}
              aria-labelledby="input-slider"
              sx={{
                color: 'primary.main', // Change the primary color of the slider
                '& .MuiSlider-thumb': {
                  color: 'secondary.main', // Change the color of the thumb
                },
                '& .MuiSlider-rail': {
                  color: 'secon', // Change the color of the rail
                },
              }}
            />
          </Grid>
          <Grid item>
            <Input
              value={value}
              size="small"
              onChange={handleInputChange}
              onBlur={handleBlur}
              inputProps={{
                step: 5,
                min: min,
                max: max,
                type: 'number',
                'aria-labelledby': 'input-slider',
              }}
              sx={{fontFamily: 'Kavoon'}}
            />
          </Grid>
        </Grid>
      </Box>
    );
  }

export default SliderInput;